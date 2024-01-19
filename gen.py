import argparse
from random import *

class EntityGenerator:
    def __init__(self, planes, towers, delay, path):
        self.planes = planes
        self.towers = towers
        self.delay = delay  # Nouveau paramètre pour le délai
        self.path = path
        self.entities = []

    def generate_entities(self):
        for _ in range(self.planes):
            start_x, start_y = format(uniform(1, 1919), '.6f'), format(uniform(1, 1079), '.6f')
            end_x, end_y = format(uniform(1, 1919), '.6f'), format(uniform(1, 1079), '.6f')
            speed = format(uniform(1, 12), '.6f')
            delay = format(uniform(0, self.delay), '.6f')  # Utilisation du délai max
            entity = f"A  {start_x} {start_y}  {end_x} {end_y}  {speed}  {delay}"
            self.entities.append(entity)

        for _ in range(self.towers):
            tower_x, tower_y = format(uniform(1, 1919), '.6f'), format(uniform(1, 1079), '.6f')
            radius = format(uniform(5, 10), '.6f')
            entity = f"T  {tower_x} {tower_y}  {radius}"
            self.entities.append(entity)

    def save_entities(self):
        with open(self.path, 'w') as file:
            file.write('\n'.join(self.entities))

if __name__ == "__main__":
    parser = argparse.ArgumentParser()
    parser.add_argument('-p', '--planes', required=True, type=int, help="Number of planes")
    parser.add_argument('-t', '--towers', required=True, type=int, help="Number of towers")
    parser.add_argument('-d', '--delay', required=True, type=float, help="Maximum delay in seconds")
    parser.add_argument('-pa', '--path', required=True, type=str, help="Path to the output file")
    args = parser.parse_args()

    generator = EntityGenerator(args.planes, args.towers, args.delay, args.path)
    generator.generate_entities()
    generator.save_entities()
